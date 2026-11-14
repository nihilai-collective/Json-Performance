
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10145.6 | 0.423097 | 513.211ms | 56369 | 2560 | 1.2866e+06 | 5298.6 | 1.93226 | 1(Win) | true |
| simdjson (reflection) | 9312.23 | 0.643161 | 625.165ms | 56369 | 320 | 441125 | 5772.8 | 1.60894 | 2(Loss) | true |
| Glaze | 2476.31 | 0.657824 | 2275.1ms | 56369 | 320 | 6.52591e+06 | 21708.8 | 0.242629 | 3(Loss) | true |
