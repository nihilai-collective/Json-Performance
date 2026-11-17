
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1920.96 | 0.256686 | 9055.86ms | 631514 | 1280 | 8.28977e+08 | 313520 | 0.339118 | 1.28869 | 1(Win) | true |
| Jsonifier | 1624.78 | 0.237686 | 5379.06ms | 631514 | 320 | 2.48391e+08 | 370671 | 0.351186 | 1.52364 | 2(Loss) | true |
| Glaze | 1560.4 | 0.204624 | 5480.53ms | 631514 | 80 | 4.99e+07 | 385965 | 0.274741 | 1.58652 | 3(Loss) | true |
| simdjson (ondemand) | 1407 | 0.141295 | 5918.03ms | 631514 | 640 | 2.34105e+08 | 428044 | 0.182814 | 1.75944 | 4(Loss) | true |
