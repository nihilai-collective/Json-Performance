
----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7374.1 | 0.333333 | 200.102ms | 14795 | 2560 | 104138 | 1913.4 | 0.48887 | 1(Win) | true |
| Glaze | 3101.15 | 0.462656 | 482.469ms | 14795 | 1280 | 567168 | 4549.8 | 1.22364 | 2(Loss) | true |
| simdjson (reflection) | 337.341 | 0.162641 | 4249.68ms | 14795 | 640 | 2.96165e+06 | 41826 | 0.159455 | 3(Loss) | true |
