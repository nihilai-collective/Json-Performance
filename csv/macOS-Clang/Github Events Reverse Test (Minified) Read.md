
----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 923.554 | 0.0577961 | 5513.29ms | 53331 | 4890 | 4.95383e+06 | 55070.3 | 0.136402 | 1(Win) | true |
| simdjson (ondemand) | 341.522 | 0.260786 | 7761.43ms | 53331 | 320 | 4.82658e+07 | 148923 | 0.00969976 | 2(Loss) | true |
