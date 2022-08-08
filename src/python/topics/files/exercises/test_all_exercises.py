import tempfile
import os
from ex_1_two_words import *
from ex_2_web_response import *


##########################   EX 1 TESTS   ######################################

def test_is_valid_arg():
    with tempfile.TemporaryFile() as tf:
        assert is_valid_argv(["ex_1_two_words.py", tf.name])
        assert not is_valid_argv(["ex_1_two_words.py", "gavgav", tf.name])
        assert not is_valid_argv(["ex_1_two_words.py", tf.name, "meow"])

    assert not is_valid_argv(["asd, not_existing_file.docx"])


def test_get_file_content():
    text = "ljdsbhf wef bifbwk jfiwef kwdjnfi enksdfn winfw"
    with tempfile.NamedTemporaryFile("w+t", delete=False) as tf:
        tf.write(text)
        tf.close()
        assert get_file_content(tf.name) == text


def test_remove_ignored():
    cases = [
        (
            '.!"\'#$%&()*+-,/:;<=>?@[\\]^_{|}~',
             " " * len('.!"\'#$%&()*+-,/:;<=>?@[\\]^_{|}~')
        ),
        ("Johnas.", "Johnas "),
        ("Johnas,", "Johnas "),
        ("'Johnas'", " Johnas "),
    ]
    for initial, final in cases:
        assert remove_ignored(initial) == final


ALPHAS_ENG = ["asd", "Adasd", "ASDASD", "John"]
ALPHAS_RU = ["Федор", "фывфыв", "щшщштщт"]
NOT_ALPHAS = ["asd!@#", "1231asdasd", "фыв213,,?"]


def test_is_eng_alpha():
    for eng_alpha in ALPHAS_ENG:
        assert is_eng_alpha(eng_alpha)
    for ru_alpha in ALPHAS_RU:
        assert not is_eng_alpha(ru_alpha)
    for not_alpha in NOT_ALPHAS:
        assert not is_eng_alpha(not_alpha)


def test_is_ru_alpha():
    for eng_alpha in ALPHAS_ENG:
        assert not is_ru_alpha(eng_alpha)
    for ru_alpha in ALPHAS_RU:
        assert is_ru_alpha(ru_alpha)
    for not_alpha in NOT_ALPHAS:
        assert not is_ru_alpha(not_alpha)


def test_is_alpha():
    for eng_alpha in ALPHAS_ENG:
        assert is_alpha(eng_alpha)
    for ru_alpha in ALPHAS_RU:
        assert is_alpha(ru_alpha)
    for not_alpha in NOT_ALPHAS:
        assert not is_ru_alpha(not_alpha)


def test_count_words():
    text1 = "L L L A A A B B C C C C C C".split()
    dict1 = {"L": 3, "A": 3, "B": 2, "C": 6}
    assert count_words(text1) == dict1

    text2 = "L D L A A A A A B B C C A C C C D".split()
    dict2 = {"L": 2, "A": 6, "B": 2, "C": 5, "D": 2}
    assert count_words(text2) == dict2


def test_most_common_word():
    text1 = "L L L A A A B B C C C C C C"
    assert most_common_word(text1) == "C"
    text2 = "L D L A A A A A B B C C A C C C D"
    assert most_common_word(text2) == "A"


def test_longest_eng_word():
    text1 = "L L L AA A AA B BBBB C C C C C C"
    assert longest_eng_word(text1) == "BBBB"
    text2 = "L D L A A ZaZa A A B B C C A Jacob C C C D"
    assert longest_eng_word(text2) == "Jacob"


##########################   EX 2 TESTS   ######################################


def test_get_json_content():
    text = '{"a": 1, "b": 2, "c": 3}'
    dic = {'a': 1, 'b': 2, 'c': 3}
    with tempfile.NamedTemporaryFile("w+t", delete=False) as tf:
        tf.write(text)
        tf.close()
        assert get_json_content(tf.name) == dic


valid_test_obj = {
    "timestamp": 1555296322000,
    "referer": "https://b24-mu3bxs.bitrix24.shop//katalog/clothes/t-shirts/",
    "location": "https://b24-mu3bxs.bitrix24.shop/",
    "remoteHost": "test0",
    "partyId": "0:aFpLgMBB:BcYmReGvvFOxrDyWtwCqiHHYMmKlLWiH",
    "sessionId": "0:NynteeXG:MYlskrqZbcmXNSFEJaZIsNVGeDLLpmct",
    "pageViewId": "0:EbVCtAYF:TKbcptzZYKGKBCRzjGIfbojjhNoXXFwu",
    "eventType": "itemViewEvent",
    "item_id": "bx_WEpJouEp_RIXLTRMhVimqPmwQONbDxdJAKqptFOCZ",
    "item_price": 11907,
    "item_url": "https://b24-mu3bxs.bitrix24.shop//katalog/item/dress-spring-ease/",
    "basket_price": "",
    "detectedDuplicate": False,
    "detectedCorruption": False,
    "firstInSession": False,
    "userAgentName": "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; .NET CLR 1.1.4322; .NET4.0C; Tablet PC 2.0)"
}

invalid_test_obj_nourl = {
    "timestamp": 1555296322000,
    "referer": "ahttps://b24-mu3bxs.bitrix24.shop//katalog/clothes/t-shirts/",
    "location": "https://b24-mu3bxs.bitrix24.shop/",
    "remoteHost": "test0",
    "partyId": "0:aFpLgMBB:BcYmReGvvFOxrDyWtwCqiHHYMmKlLWiH",
    "sessionId": "0:NynteeXG:MYlskrqZbcmXNSFEJaZIsNVGeDLLpmct",
    "pageViewId": "0:EbVCtAYF:TKbcptzZYKGKBCRzjGIfbojjhNoXXFwu",
    "eventType": "itemViewEvent",
    "item_id": "bx_WEpJouEp_RIXLTRMhVimqPmwQONbDxdJAKqptFOCZ",
    "item_price": 11907,
    "item_url": "https://b24-mu3bxs.bitrix24.shop//katalog/item/dress-spring-ease/",
    "basket_price": "",
    "detectedDuplicate": False,
    "detectedCorruption": False,
    "firstInSession": False,
    "userAgentName": "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; .NET CLR 1.1.4322; .NET4.0C; Tablet PC 2.0)"
}

invalid_test_obj_key_miss = {
    "timestamp": 1555296322000,
    "referer": "https://b24-mu3bxs.bitrix24.shop//katalog/clothes/t-shirts/",
    "location": "https://b24-mu3bxs.bitrix24.shop/",
    "remoteHost": "test0",
    "partyId": "0:aFpLgMBB:BcYmReGvvFOxrDyWtwCqiHHYMmKlLWiH",
    "sessionId": "0:NynteeXG:MYlskrqZbcmXNSFEJaZIsNVGeDLLpmct",
    "pageViewId": "0:EbVCtAYF:TKbcptzZYKGKBCRzjGIfbojjhNoXXFwu",
    "eventType": "itemViewEvent",
    "item_url": "https://b24-mu3bxs.bitrix24.shop//katalog/item/dress-spring-ease/",
    "basket_price": "",
    "detectedDuplicate": False,
    "detectedCorruption": False,
    "firstInSession": False,
    "userAgentName": "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; .NET CLR 1.1.4322; .NET4.0C; Tablet PC 2.0)"
}

invalid_test_obj_extra_keys = {
    "timestamp": 1555296322000,
    "referer": "https://b24-mu3bxs.bitrix24.shop//katalog/clothes/t-shirts/",
    "location": "https://b24-mu3bxs.bitrix24.shop/",
    "remoteHost": "test0",
    "partyId": "0:aFpLgMBB:BcYmReGvvFOxrDyWtwCqiHHYMmKlLWiH",
    "sessionId": "0:NynteeXG:MYlskrqZbcmXNSFEJaZIsNVGeDLLpmct",
    "pageViewId": "0:EbVCtAYF:TKbcptzZYKGKBCRzjGIfbojjhNoXXFwu",
    "eventType": "itemViewEvent",
    "item_id": "bx_WEpJouEp_RIXLTRMhVimqPmwQONbDxdJAKqptFOCZ",
    "item_price": 11907,
    "item_url": "https://b24-mu3bxs.bitrix24.shop//katalog/item/dress-spring-ease/",
    "basket_price": "",
    "detectedDuplicate": False,
    "detectedCorruption": False,
    "firstInSession": False,
    "some_redundant_key": "abrakadabra",
    "userAgentName": "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; .NET CLR 1.1.4322; .NET4.0C; Tablet PC 2.0)"
}

def test_all_keys_present():
    assert all_keys_present(valid_test_obj)
    assert all_keys_present(invalid_test_obj_nourl)
    assert all_keys_present(invalid_test_obj_extra_keys)
    assert not all_keys_present(invalid_test_obj_key_miss)


def test_has_only_required_keys():
    assert has_only_required_keys(valid_test_obj)
    assert has_only_required_keys(invalid_test_obj_nourl)
    assert not has_only_required_keys(invalid_test_obj_extra_keys)
    assert has_only_required_keys(invalid_test_obj_key_miss)


def test_valid_keyset_naive_impl():
    assert valid_keyset_naive_impl(valid_test_obj)
    assert valid_keyset_naive_impl(invalid_test_obj_nourl)
    assert not valid_keyset_naive_impl(invalid_test_obj_extra_keys)
    assert not valid_keyset_naive_impl(invalid_test_obj_key_miss)


def test_valid_keyset():
    assert valid_keyset(valid_test_obj)
    assert valid_keyset(invalid_test_obj_nourl)
    assert not valid_keyset(invalid_test_obj_extra_keys)
    assert not valid_keyset(invalid_test_obj_key_miss)


def test_check_url():
    assert not check_url(123)
    assert not check_url([123])
    assert not check_url(["asdasd"])
    assert not check_url("asdasd")
    assert check_url(valid_test_obj["referer"])
    assert check_url(valid_test_obj["location"])
    assert check_url(valid_test_obj["item_url"])
    assert not check_url(invalid_test_obj_nourl["referer"])
    assert check_url(invalid_test_obj_nourl["location"])
    assert check_url(invalid_test_obj_nourl["item_url"])


def test_check_legal_values():
    assert not check_legal_values("eventType", "asd")
    assert not check_legal_values("eventType", "aasdas")
    assert not check_legal_values("eventType", "azazaz")
    assert check_legal_values("eventType", "itemBuyEvent")
    assert check_legal_values("eventType", "itemViewEvent")


def test_check_correct_type():
    assert check_correct_type(123, int)
    assert check_correct_type("asd", str)
    assert check_correct_type(True, bool)
    assert not check_correct_type(123, str)
    assert not check_correct_type(123, bool)
    assert not check_correct_type(True, int)
    assert not check_correct_type("abc", int)


def test_check_obj_field():
    for key in valid_test_obj:
        assert check_obj_field(valid_test_obj, key)
    assert not check_obj_field(valid_test_obj, "non_existing_field")


def test_check_objects():
    assert check_objects([valid_test_obj])
    assert not check_objects([valid_test_obj, invalid_test_obj_nourl])
    assert not check_objects([valid_test_obj, invalid_test_obj_key_miss])
    assert not check_objects([valid_test_obj, invalid_test_obj_extra_keys])
