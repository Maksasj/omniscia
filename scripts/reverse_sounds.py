import os
from moviepy.audio.io.AudioFileClip import AudioFileClip
from moviepy.video.io.VideoFileClip import VideoFileClip
import moviepy.video.fx.all as vfx

def reverse_audio(input_file_path, output_file_path):
    audio = AudioFileClip(input_file_path)
    video_clip = VideoFileClip("assets/gif.gif")
    video_clip = video_clip.set_audio(audio)
    video_clip = video_clip.fx(vfx.time_mirror)

    newAudio = video_clip.audio
    newAudio.write_audiofile(output_file_path)

def reverse_wav_files_recursive(directory_path):
    fileList = []

    for root, dirs, files in os.walk(directory_path):
        for filename in files:
            if filename.endswith('.wav'):
                input_file_path = os.path.join(root, filename)
                output_file_path = os.path.join(root, f'reversed_{filename}')
                fileList.append((input_file_path, output_file_path))
    
    for filePair in fileList:
        reverse_audio(filePair[0], filePair[1])

reverse_wav_files_recursive("assets")