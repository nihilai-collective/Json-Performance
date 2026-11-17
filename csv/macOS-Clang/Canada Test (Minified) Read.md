
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7119.64 | 0.173296 | 7907.87ms | 2251027 | 1280 | 3.49489e+08 | 301525 | 0.485768 | 1(Win) | true |
| simdjson (stage-1) | 5199.47 | 0.941967 | 5376.66ms | 2251027 | 30 | 4.5377e+08 | 412878 | 0.233912 | 2(Loss) | true |
