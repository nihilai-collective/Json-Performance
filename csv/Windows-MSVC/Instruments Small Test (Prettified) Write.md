
----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10571.4 | 0.225188 | 97.3512ms | 9249 | 640 | 2259.39 | 834.375 | 0.558659 | 0.226185 | 1(Win) | true |
| Glaze | 3418.05 | 0.217599 | 262.264ms | 9249 | 4890 | 154190 | 2580.57 | 0.382022 | 0.715994 | 2(Loss) | true |
