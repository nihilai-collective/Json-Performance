
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.596 | 0.113366 | 442.057ms | 3873 | 80 | 1821.2 | 4208.75 | 0.325636 | 3.4449 | 1(Win) | true |
| simdjson (ondemand) | 609.753 | 0.0918166 | 612.245ms | 3873 | 80 | 2474.68 | 6057.5 | 0.0824742 | 4.96542 | 2(Loss) | true |
