
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 19626.5 | 0.121842 | 8934.9ms | 1834197 | 2560 | 3.01885e+07 | 89125.6 | 0.617391 | 0.126104 | 1(Win) | true |
| simdjson (stage-1) | 16185.8 | 0.420072 | 5568.05ms | 1834197 | 160 | 3.29756e+07 | 108072 | 0.442758 | 0.152911 | 2(Loss) | true |
