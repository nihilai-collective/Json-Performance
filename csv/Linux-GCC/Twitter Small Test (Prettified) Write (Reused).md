
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14136.4 | 0.0529845 | 757.295ms | 4300 | 320 | 7.55972 | 290.087 | 0.0517353 | 0.40861 | 0.951395 | 0.134884 | 0.000232558 | 1.23547e-05 | 6.5407e-06 | 1(Win) | true |
| Glaze | 4236.06 | 0.552919 | 828.282ms | 4300 | 640 | 18336.4 | 968.069 | 0.505531 | 1.25837 | 3.03163 | 0.47721 | 0.00072202 | 3.08866e-05 | 9.44767e-06 | 2(Loss) | true |
| simdjson (reflection) | 552.886 | 0.0941237 | 1484.8ms | 4300 | 2560 | 124768 | 7417.09 | 0.0123411 | 9.1965 | 33.5838 | 7.41082 | 0.0106289 | 0.000349564 | 0.000222202 | 3(Loss) | true |
