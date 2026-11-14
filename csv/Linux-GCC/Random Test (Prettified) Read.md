
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19640 | 0.124521 | 3645.28ms | 728486 | 2560 | 4.96689e+06 | 35373.6 | 0.815412 | 0.125961 | 1(Win) | true |
| simdjson (stage-1) | 16196.8 | 0.264778 | 4309.24ms | 728486 | 320 | 4.1276e+06 | 42893.5 | 0.111914 | 0.152752 | 2(Loss) | true |
