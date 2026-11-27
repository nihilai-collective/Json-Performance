
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5781.68 | 0.541667 | 5366.25ms | 5212421 | 320 | 6.94043e+09 | 859777 | 1.31779 | 1(Win) | true |
| simdjson (ondemand) | 5445.4 | 0.309203 | 5822.13ms | 5212421 | 160 | 1.27475e+09 | 912872 | 0.00798173 | 2(Loss) | true |
