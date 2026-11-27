
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 399.292 | 0.109057 | 6586.08ms | 1834197 | 80 | 1.82602e+09 | 4.38082e+06 | 0.291619 | 12.6893 | 59.4419 | 13.354 | 0.0438606 | 0.344027 | 0.0120285 | 1(Win) | true |
| simdjson (ondemand) | 272.403 | 0.164649 | 9655.78ms | 1834197 | 30 | 3.35358e+09 | 6.42148e+06 | 0.146963 | 18.5371 | 101.258 | 20.9693 | 0.041967 | 0.788779 | 0.0218274 | 2(Loss) | true |
