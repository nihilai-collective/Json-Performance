
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2638.33 | 0.270441 | 147.13ms | 3873 | 30 | 430.033 | 1399.97 | 0.987788 | 1(Win) | true |
| Jsonifier (two-stage) | 2617.33 | 0.273295 | 155.649ms | 3873 | 30 | 446.234 | 1411.2 | 0.108773 | 2(Loss) | true |
| Glaze | 1376.32 | 0.0467397 | 277.64ms | 3873 | 640 | 1006.95 | 2683.67 | 0.399146 | 3(Loss) | true |
| simdjson (ondemand) | 641.319 | 0.230089 | 630.685ms | 3873 | 640 | 112387 | 5759.35 | 0.0501107 | 4(Loss) | true |
