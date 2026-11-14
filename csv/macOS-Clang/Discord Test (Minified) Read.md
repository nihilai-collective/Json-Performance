
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5471.59 | 0.1331 | 987.71ms | 56369 | 4890 | 836212 | 9824.87 | 0.0697364 | 1(Win) | true |
| simdjson (stage-1) | 5345.44 | 0.133508 | 1011.01ms | 56369 | 4890 | 881527 | 10056.7 | 0.0957397 | 2(Loss) | true |
