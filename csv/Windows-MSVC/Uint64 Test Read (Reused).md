
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 537.217 | 0.430222 | 220.076ms | 1213 | 30 | 2574.71 | 2153.33 | 0 | 4.55474 | 1(Win) | true |
| simdjson (ondemand) | 300.031 | 0.102191 | 391.24ms | 1213 | 160 | 2483.88 | 3855.62 | 0.0811162 | 8.18666 | 2(Loss) | true |
