
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3314.02 | 0.230831 | 114.109ms | 3873 | 2560 | 16943.9 | 1114.53 | 0.105256 | 0.902529 | 1(Win) | true |
| simdjson (stage-1) | 1137.28 | 0.11068 | 327.71ms | 3873 | 1280 | 16539 | 3247.73 | 0.170501 | 2.65363 | 2(Loss) | true |
