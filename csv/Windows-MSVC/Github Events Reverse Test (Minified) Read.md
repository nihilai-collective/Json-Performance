
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 677.671 | 0.135484 | 7501.52ms | 53331 | 4890 | 5.05603e+07 | 75051.8 | 0.00754513 | 4.48335 | 1(Win) | true |
| simdjson (ondemand) | 356.782 | 0.222446 | 7286.54ms | 53331 | 1280 | 1.2871e+08 | 142553 | 0.0927598 | 8.51706 | 2(Loss) | true |
