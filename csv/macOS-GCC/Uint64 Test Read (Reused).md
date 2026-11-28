
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1645.76 | 1.29758 | 73.4651ms | 1213 | 2560 | 212959 | 702.9 | 0.15625 | 1(Win) | true |
| Glaze | 935.625 | 0.759979 | 126.98ms | 1213 | 2560 | 226027 | 1236.4 | 0.7386 | 2(Loss) | true |
| simdjson (reflection) | 756.034 | 0.68013 | 160.758ms | 1213 | 2560 | 277245 | 1530.1 | 0.591216 | 3(Loss) | true |
| simdjson (ondemand) | 255.981 | 0.270328 | 462.22ms | 1213 | 4890 | 729789 | 4519.11 | 1.44145 | 4(Loss) | true |
