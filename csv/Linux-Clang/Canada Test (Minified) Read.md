
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 781.227 | 0.694031 | 8323.73ms | 2251027 | 40 | 1.45487e+10 | 2.74792e+06 | 0.488172 | 3.16903 | 1(Win) | true |
| Jsonifier (two-stage) | 719.323 | 0.116093 | 9412.71ms | 2251027 | 160 | 1.92065e+09 | 2.9844e+06 | 0.587668 | 3.44176 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 713.175 | 0.180511 | 9476.32ms | 2251027 | 160 | 4.72384e+09 | 3.01012e+06 | 2.56491 | 3.47139 | -(Loss) | false |
| simdjson (ondemand) | 688.189 | 0.137497 | 9774.69ms | 2251027 | 30 | 5.5189e+08 | 3.11942e+06 | 0.209649 | 3.59745 | 4(Loss) | true |
