
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15375.1 | 0.162859 | 341.747ms | 53331 | 640 | 18574.9 | 3307.97 | 0.0330532 | 0.195586 | 1(Win) | true |
| simdjson (stage-1) | 12704.8 | 0.417993 | 403.134ms | 53331 | 2560 | 716805 | 4003.24 | 0.0458402 | 0.236728 | 2(Loss) | true |
