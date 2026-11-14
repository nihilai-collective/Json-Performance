
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 905.467 | 0.159355 | 496.749ms | 4669 | 1280 | 78604 | 4917.58 | 0.00476584 | 3.34123 | 1(Win) | true |
| simdjson (ondemand) | 811.647 | 0.134885 | 549.433ms | 4669 | 2560 | 140180 | 5486.02 | 0.0242151 | 3.73054 | 2(Loss) | true |
