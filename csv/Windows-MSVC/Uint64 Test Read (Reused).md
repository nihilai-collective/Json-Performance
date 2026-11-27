
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 647.589 | 0.161769 | 187.304ms | 1213 | 1280 | 10688.6 | 1786.33 | 0.0568878 | 4.62375 | 1(Win) | true |
| simdjson (ondemand) | 336.045 | 0.0975636 | 354.344ms | 1213 | 1280 | 14438.2 | 3442.42 | 0.106552 | 8.96766 | 2(Loss) | true |
