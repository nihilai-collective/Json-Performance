
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8089.92 | 0.0272316 | 6428.08ms | 466906 | 2560 | 575117 | 55040.9 | 0.15734 | 0.624325 | 3.05908 | 0.364988 | 0.000873718 | 2.76337e-06 | 1.44652e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 8079.55 | 0.0396072 | 6419.06ms | 466906 | 1280 | 609877 | 55111.5 | 0.0373421 | 0.62527 | 3.05793 | 0.364714 | 0.000870496 | 1.6699e-06 | 4.5847e-07 | 2(Loss) | true |
| simdjson (reflection) | 7073.53 | 0.020455 | 7096.42ms | 466906 | 2560 | 424449 | 62949.7 | 0.0815624 | 0.714513 | 3.55191 | 0.367929 | 0.00100136 | 1.15371e-06 | 3.48872e-07 | 3(Loss) | true |
| simdjson (ondemand) | 6819.21 | 0.0274961 | 7322.95ms | 466906 | 1280 | 412613 | 65297.3 | 0.152171 | 0.738417 | 3.56518 | 0.364907 | 0.000793742 | 1.41724e-06 | 4.33371e-07 | 4(Loss) | true |
| Glaze | 3253.71 | 0.0397158 | 7436.91ms | 466906 | 2560 | 7.56255e+06 | 136852 | 0.0487667 | 1.55 | 6.4004 | 1.01743 | 0.00151032 | 5.60873e-06 | 3.6778e-06 | 5(Loss) | true |
