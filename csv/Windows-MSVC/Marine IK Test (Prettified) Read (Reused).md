
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2513.31 | 0.0910858 | 9891.21ms | 7351818 | 40 | 2.58261e+08 | 2.78964e+06 | 0.239896 | 0.985066 | 1(Win) | true |
| Jsonifier | 2341.61 | 0.341607 | 5014.73ms | 7351818 | 80 | 8.36957e+09 | 2.9942e+06 | 0.538167 | 1.0573 | 2(Loss) | true |
| simdjson (ondemand) | 866.532 | 0.0782017 | 5972.67ms | 7351818 | 40 | 1.60145e+09 | 8.09115e+06 | 1.87193 | 2.85715 | 3(Loss) | true |
| Glaze | 785.618 | 0.46406 | 6533.1ms | 7351818 | 30 | 5.1456e+10 | 8.92449e+06 | 2.09433 | 3.15142 | 4(Loss) | true |
