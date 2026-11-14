
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1725.44 | 0.181268 | 7115.03ms | 409725 | 80 | 1.34808e+07 | 226460 | 0.0231885 | 2.94805 | 15.1566 | 2.85924 | 0.00607331 | 0.00667457 | 2.22405e-05 | 1(Win) | true |
| simdjson (ondemand) | 1159.93 | 0.202411 | 9884ms | 409725 | 40 | 1.85974e+07 | 336870 | 0.0282013 | 4.3696 | 17.1013 | 3.14597 | 0.0128806 | 0.0117146 | 1.07389e-05 | 2(Loss) | true |
