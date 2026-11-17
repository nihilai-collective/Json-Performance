
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1343.07 | 0.0630673 | 671.827ms | 8051 | 4890 | 63565.5 | 5716.79 | 0.239594 | 2.2551 | 1(Win) | true |
| Jsonifier | 1188.29 | 0.0700965 | 748.006ms | 8051 | 2560 | 52515.4 | 6461.41 | 0.0387062 | 2.55038 | 2(Loss) | true |
| Glaze | 1100.82 | 0.0571866 | 797.434ms | 8051 | 4890 | 77797.3 | 6974.83 | 0.0204741 | 2.75274 | 3(Loss) | true |
| simdjson (ondemand) | 887.626 | 0.127944 | 974.135ms | 8051 | 1280 | 156779 | 8650.08 | 0.130789 | 3.4154 | 4(Loss) | true |
