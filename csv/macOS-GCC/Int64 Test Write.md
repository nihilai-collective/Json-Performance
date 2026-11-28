
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 307.629 | 1.39334 | 425.008ms | 1313 | 30 | 96496.1 | 4070.4 | 0.625 | 1(Win) | true |
| simdjson (reflection) | 277.582 | 0.345209 | 463.999ms | 1313 | 2560 | 620798 | 4511 | 0.289017 | 2(Loss) | true |
| Glaze | 178.719 | 0.173321 | 730.419ms | 1313 | 160 | 23594.5 | 7006.4 | 0.0685558 | 3(Loss) | true |
