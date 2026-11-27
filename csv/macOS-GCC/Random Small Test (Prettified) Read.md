
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1377.9 | 0.488073 | 577.536ms | 8150 | 320 | 242549 | 5640.8 | 0.0425291 | 1(Win) | true |
| simdjson (ondemand) | 926.173 | 0.812163 | 855.3ms | 8150 | 1280 | 5.94603e+06 | 8392 | 0.291601 | 2(Loss) | true |
