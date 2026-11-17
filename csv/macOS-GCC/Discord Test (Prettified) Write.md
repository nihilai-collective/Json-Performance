
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11173.8 | 0.555522 | 702.396ms | 94370 | 640 | 1.2813e+06 | 8054.4 | 0.962696 | 1(Win) | true |
| Glaze | 2160.51 | 1.09141 | 4406.14ms | 94370 | 160 | 3.30715e+07 | 41656 | 4.95445 | 2(Loss) | true |
| simdjson (reflection) | 309.782 | 0.320742 | 7803.37ms | 94370 | 1280 | 1.11141e+09 | 290521 | 1.06293 | 3(Loss) | true |
