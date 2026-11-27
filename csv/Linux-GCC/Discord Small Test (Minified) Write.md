
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11159.8 | 0.188597 | 761.939ms | 4857 | 80 | 49.0214 | 415.062 | 0.268752 | 0.507744 | 1.65905 | 0.241713 | 0.000205888 | 2.31624e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7853.84 | 0.20685 | 778.081ms | 4857 | 80 | 119.063 | 589.775 | 0.127006 | 0.700399 | 2.06691 | 0.330245 | 0.000205888 | 2.57361e-05 | 5.14721e-06 | 2(Loss) | true |
| Glaze | 4136.26 | 0.21067 | 831.398ms | 4857 | 1280 | 7124.25 | 1119.85 | 0.0498561 | 1.30237 | 3.72967 | 0.610665 | 0.000415798 | 5.51717e-05 | 6.27316e-06 | 3(Loss) | true |
