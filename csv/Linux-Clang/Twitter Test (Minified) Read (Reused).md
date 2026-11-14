
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2317.89 | 0.0973459 | 5863.81ms | 466906 | 1280 | 4.47628e+07 | 192104 | 0.0499492 | 2.18046 | 6.83481 | 1.13322 | 0.00889911 | 0.00262865 | 8.4474e-05 | 1(Win) | true |
| Glaze | 2304.91 | 0.123082 | 5849.34ms | 466906 | 160 | 9.04609e+06 | 193186 | 0.00760659 | 2.19292 | 8.57808 | 1.46085 | 0.00956044 | 0.00104511 | 8.37963e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2253.29 | 0.0796939 | 6052ms | 466906 | 1280 | 3.17456e+07 | 197611 | 0.607601 | 2.24189 | 7.78353 | 1.19749 | 0.00993829 | 0.00768706 | 4.85995e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1055.52 | 0.217964 | 5826.08ms | 466906 | 80 | 6.76368e+07 | 421854 | 0.300505 | 4.75633 | 16.7911 | 2.85008 | 0.0100122 | 0.0101927 | 3.42949e-05 | 4(Loss) | true |
