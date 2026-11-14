
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 11756.9 | 5.43172 | 35.3421ms | 4300 | 640 | 229725 | 348.8 | 6.83761 | -(Win) | false |
| Glaze | 2984.57 | 0.723668 | 141.731ms | 4300 | 2560 | 253100 | 1374 | 2.39976 | 2(Loss) | true |
| simdjson (reflection) | 360.833 | 0.48425 | 1200.57ms | 4300 | 1280 | 3.8768e+06 | 11364.8 | 0.292986 | 3(Loss) | true |
