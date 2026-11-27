
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3744.85 | 0.0313051 | 2525.12ms | 56369 | 4890 | 98753.1 | 14355.1 | 0.0393272 | 1.37292 | 6.87239 | 1.26353 | 0.00165641 | 1.76931e-05 | 1.02886e-05 | 1(Win) | true |
| Glaze | 2998.01 | 0.0665812 | 2862.84ms | 56369 | 4890 | 696988 | 17931.1 | 0.141547 | 1.70498 | 8.91579 | 1.74675 | 0.00217277 | 1.37169e-05 | 7.94502e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2350.02 | 0.0650525 | 3353.6ms | 56369 | 320 | 70862.3 | 22875.4 | 0.00178962 | 2.15777 | 10.8042 | 1.75708 | 0.00292559 | 1.61325e-05 | 1.04778e-05 | 3(Loss) | true |
| simdjson (reflection) | 1901.94 | 0.108785 | 3950.33ms | 56369 | 80 | 75634 | 28264.7 | 0.0954785 | 2.71004 | 11.9912 | 1.93965 | 0.00253952 | 1.68532e-05 | 9.97889e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1647.83 | 0.0722544 | 4378.79ms | 56369 | 640 | 355604 | 32623.4 | 0.0782595 | 3.10656 | 12.8092 | 2.23988 | 0.00824664 | 1.87104e-05 | 9.67398e-06 | 5(Loss) | true |
