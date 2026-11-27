
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13744 | 0.49075 | 8327.34ms | 2251027 | 160 | 9.4011e+07 | 156196 | 0.230349 | 0.220981 | 1(Win) | true |
| simdjson (stage-1) | 10361.8 | 0.182998 | 5431.24ms | 2251027 | 1280 | 1.8399e+08 | 207179 | 0.177782 | 0.29318 | 2(Loss) | true |
