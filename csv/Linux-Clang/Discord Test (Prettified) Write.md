
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17119.8 | 0.0423342 | 506.706ms | 94370 | 30 | 148.585 | 5256.97 | 0.0386938 | 0.14388 | 1(Win) | true |
| Glaze | 3458.56 | 0.253505 | 2607.43ms | 94370 | 320 | 1.39252e+06 | 26021.9 | 0.108175 | 0.715143 | 2(Loss) | true |
