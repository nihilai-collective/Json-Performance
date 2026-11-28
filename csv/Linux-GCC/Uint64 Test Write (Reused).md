
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2711.21 | 0.217603 | 51.2089ms | 1213 | 40 | 34.4814 | 426.675 | 0.38716 | 0.863623 | 1(Win) | true |
| simdjson (reflection) | 2557.89 | 0.0698682 | 53.5065ms | 1213 | 160 | 15.9748 | 452.25 | 0.127304 | 0.912217 | 2(Loss) | true |
| Glaze | 1354.68 | 0.385948 | 94.8548ms | 1213 | 30 | 325.857 | 853.933 | 0.0390198 | 1.77469 | 3(Loss) | true |
