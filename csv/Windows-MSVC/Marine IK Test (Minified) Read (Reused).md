
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 764.218 | 0.0996029 | 8241.1ms | 1834197 | 40 | 2.07903e+08 | 2.28891e+06 | 0.1685 | 3.23959 | 1(Win) | true |
| Jsonifier (two-stage) | 699.019 | 0.139936 | 8923.15ms | 1834197 | 30 | 3.67873e+08 | 2.5024e+06 | 0.293511 | 3.54176 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 233.567 | 0.191074 | 5556.65ms | 1834197 | 40 | 8.19091e+09 | 7.4892e+06 | 3.3133 | 10.6 | -(Loss) | false |
| Glaze | 216.434 | 0.501189 | 5990.39ms | 1834197 | 40 | 6.56305e+10 | 8.08204e+06 | 0.171948 | 11.439 | 4(Loss) | true |
