
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1788.66 | 0.259871 | 215.311ms | 3873 | 80 | 2303.8 | 2065 | 0.486618 | 1.36515 | 1(Win) | true |
| Jsonifier (two-stage) | 1734.08 | 0.170621 | 219.16ms | 3873 | 160 | 2113.21 | 2130 | 0.058651 | 1.41224 | 2(Loss) | true |
| Glaze | 1225.07 | 0.133246 | 303.469ms | 3873 | 80 | 1291.14 | 3015 | 0.0829876 | 2.00085 | 3(Loss) | true |
| simdjson (ondemand) | 737.61 | 0.110485 | 533.464ms | 3873 | 40 | 1224.36 | 5007.5 | 0.3813 | 3.34125 | 4(Loss) | true |
