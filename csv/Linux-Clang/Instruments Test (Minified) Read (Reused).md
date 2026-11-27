
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2935.5 | 0.04384 | 4461.86ms | 108313 | 4890 | 1.16371e+06 | 35188.3 | 0.0983328 | 1.7355 | 7.90885 | 1.58204 | 0.00248226 | 1.53044e-05 | 8.60001e-06 | 1(Win) | true |
| Glaze | 2565.39 | 0.115344 | 4938.31ms | 108313 | 2560 | 5.52184e+06 | 40264.9 | 0.106769 | 1.96712 | 9.83716 | 1.72039 | 0.00247237 | 1.18147e-05 | 6.34013e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2189.32 | 0.0423657 | 5646.17ms | 108313 | 4890 | 1.9538e+06 | 47181.5 | 0.296504 | 2.31351 | 11.2654 | 1.96154 | 0.00256734 | 2.03436e-05 | 1.33918e-05 | 3(Loss) | true |
| simdjson (ondemand) | 745.956 | 0.0638927 | 7551.47ms | 108313 | 2560 | 2.0039e+07 | 138474 | 0.0458137 | 6.77081 | 30.2844 | 4.26578 | 0.00328393 | 5.13269e-05 | 3.61979e-05 | 4(Loss) | true |
