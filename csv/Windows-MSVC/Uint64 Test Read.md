
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2946.76 | 0.15743 | 130.268ms | 3873 | 640 | 2492.08 | 1253.44 | 0.0249252 | 0.821825 | 1(Win) | true |
| simdjson (stage-1) | 606.998 | 0.0939642 | 618.422ms | 3873 | 40 | 1307.69 | 6085 | 0.0273973 | 4.04735 | 2(Loss) | true |
