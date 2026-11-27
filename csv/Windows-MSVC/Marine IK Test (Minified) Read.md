
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 6884.28 | 0.438281 | 6592.43ms | 1834197 | 1280 | 1.58741e+09 | 254090 | 0.844439 | 0.441162 | 1(Win) | true |
| simdjson (stage-1) | 5688.94 | 0.605341 | 7784.41ms | 1834197 | 1280 | 4.43444e+09 | 307478 | 2.0905 | 0.533924 | 2(Loss) | true |
