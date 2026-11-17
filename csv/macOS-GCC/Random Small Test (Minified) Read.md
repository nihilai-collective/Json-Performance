
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1149.02 | 0.186926 | 419.082ms | 5094 | 4890 | 305432 | 4227.98 | 0.679397 | 1(Win) | true |
| Jsonifier (two-stage) | 975.831 | 0.348293 | 544.57ms | 5094 | 4890 | 1.47016e+06 | 4978.34 | 4.6314 | 2(Loss) | true |
| simdjson (reflection) | 864.724 | 0.217087 | 575.978ms | 5094 | 2560 | 380778 | 5618 | 0.457139 | 3(Loss) | true |
| Glaze | 743.009 | 0.272295 | 648.918ms | 5094 | 2560 | 811424 | 6538.3 | 1.75357 | 4(Loss) | true |
| simdjson (ondemand) | 601.895 | 0.706706 | 755.193ms | 5094 | 320 | 1.04113e+06 | 8071.2 | 1.2342 | 5(Loss) | true |
