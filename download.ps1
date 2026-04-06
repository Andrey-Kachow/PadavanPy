param(
    [Parameter(Mandatory=$true)]
    [string]$Url
)

Write-Host "Downloading: $Url"
Write-Host ""

& ".\yt-dlp.exe" `
  -x `
  --audio-format mp3 `
  --audio-quality 0 `
  --embed-metadata `
  --embed-thumbnail `
  --convert-thumbnails jpg `
  --ppa 'EmbedThumbnail+ffmpeg_o:-c:v mjpeg -vf scale="if(gt(iw,ih),ih,iw)":"if(gt(iw,ih),ih,iw)"' `
  --ppa 'EmbedThumbnail+ffmpeg_o:-q:v 2' `
  -o "%(title)s.%(ext)s" `
  "$Url"

Write-Host ""
Write-Host "Done."