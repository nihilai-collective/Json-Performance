
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15659.7 | 0.0985747 | 3707.33ms | 475954 | 80 | 65310.8 | 28985.6 | 0.372072 | 0.322975 | 1.0529 | 0.138513 | 0.00025462 | 0.00368168 | 4.56977e-06 | 1(Win) | true |
| simdjson (reflection) | 12524.5 | 0.110137 | 4388.8ms | 475954 | 30 | 47796.5 | 36241.5 | 0.0271402 | 0.396281 | 1.26996 | 0.180312 | 0.000263051 | 0.00221695 | 1.48474e-05 | 2(Loss) | true |
| Glaze | 8472.37 | 0.110007 | 6128.38ms | 475954 | 4890 | 1.6985e+07 | 53574.8 | 0.151202 | 0.59185 | 2.21522 | 0.322105 | 0.000258647 | 0.000689836 | 4.19306e-06 | 3(Loss) | true |
