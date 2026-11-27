
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10979.9 | 0.0712422 | 844.476ms | 94370 | 30 | 1022.99 | 8196.67 | 0 | 0.223935 | 1(Win) | true |
| Glaze | 3114.93 | 0.270814 | 2972.56ms | 94370 | 160 | 979566 | 28892.5 | 0.327727 | 0.794033 | 2(Loss) | true |
