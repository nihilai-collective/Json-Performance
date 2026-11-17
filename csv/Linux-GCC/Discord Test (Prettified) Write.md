
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24343.6 | 0.0774201 | 367.316ms | 94370 | 40 | 327.692 | 3697 | 0.0153254 | 0.100946 | 1(Win) | true |
| Glaze | 4924.34 | 0.269645 | 1826.88ms | 94370 | 4890 | 1.18759e+07 | 18276.2 | 0.0475049 | 0.502014 | 2(Loss) | true |
| simdjson (reflection) | 521.829 | 0.254648 | 8864.42ms | 94370 | 80 | 1.54306e+07 | 172467 | 0.961727 | 4.74299 | 3(Loss) | true |
