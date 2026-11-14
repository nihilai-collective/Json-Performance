
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 842.18 | 0.362632 | 8090.8ms | 2251027 | 30 | 2.56334e+09 | 2.54903e+06 | 0.0217551 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 583.871 | 1.50578 | 5457.82ms | 2251027 | 40 | 1.22607e+11 | 3.67675e+06 | 1.13536 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 571.986 | 0.568573 | 5638.14ms | 2251027 | 80 | 3.64296e+10 | 3.75315e+06 | 0.650383 | 2(Tie) | true |
| simdjson (reflection) | 562.628 | 0.504547 | 5785.1ms | 2251027 | 30 | 1.11184e+10 | 3.81557e+06 | 1.05596 | 4(Loss) | true |
| simdjson (ondemand) | 513.841 | 0.494494 | 6477.3ms | 2251027 | 30 | 1.2804e+10 | 4.17784e+06 | 2.35326 | 5(Loss) | true |
