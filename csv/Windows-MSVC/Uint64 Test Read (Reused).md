
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1394.79 | 0.435531 | 88.3889ms | 1213 | 160 | 2087.66 | 829.375 | 0.0753012 | 1.72776 | 1(Win) | true |
| Glaze | 415.931 | 0.181966 | 283.471ms | 1213 | 80 | 2049.05 | 2781.25 | 0.0449236 | 5.84623 | 2(Loss) | true |
| simdjson (ondemand) | 309.048 | 0.297564 | 381.831ms | 1213 | 1280 | 158796 | 3743.12 | 0.141726 | 7.95691 | 3(Loss) | true |
