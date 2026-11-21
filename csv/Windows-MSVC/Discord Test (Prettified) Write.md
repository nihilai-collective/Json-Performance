
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11184.5 | 0.11513 | 864.102ms | 94370 | 30 | 2574.71 | 8046.67 | 0.0414422 | 0.220426 | 1(Win) | true |
| Glaze | 3079.59 | 0.101929 | 2992.55ms | 94370 | 4890 | 4.339e+06 | 29224.1 | 0.0612845 | 0.803182 | 2(Loss) | true |
