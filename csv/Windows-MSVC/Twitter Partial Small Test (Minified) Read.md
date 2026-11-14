
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5051.73 | 0.255255 | 57.5708ms | 2889 | 1280 | 2480.69 | 545.391 | 0.186567 | 0.5807 | 1(Win) | true |
| Jsonifier | 4967.06 | 0.502469 | 59.2266ms | 2889 | 320 | 2485.8 | 554.688 | 0.1693 | 0.591835 | 2(Loss) | true |
| simdjson (ondemand) | 3973.2 | 0.116306 | 71.8518ms | 2889 | 1280 | 832.584 | 693.438 | 0.202384 | 0.745095 | 3(Loss) | true |
| Glaze | 2915.52 | 0.842992 | 94.6254ms | 2889 | 40 | 2538.46 | 945 | 0.531915 | 1.02314 | 4(Loss) | true |
