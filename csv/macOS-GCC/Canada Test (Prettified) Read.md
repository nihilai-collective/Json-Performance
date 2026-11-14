
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1436.69 | 1.36381 | 5316.16ms | 5373214 | 30 | 7.09855e+10 | 3.56673e+06 | 1.13725 | 1(Win) | true |
| Jsonifier (two-stage) | 1318.47 | 0.687625 | 5803.08ms | 5373214 | 30 | 2.14267e+10 | 3.88656e+06 | 0.629909 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1155.34 | 0.445605 | 6864.52ms | 5373214 | 30 | 1.17185e+10 | 4.43533e+06 | 0.657106 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE DID NOT CONVERGE | 1131 | 0.991937 | 6526.47ms | 5373214 | 80 | 1.61585e+11 | 4.53076e+06 | 8.98514 | -(Tie) | false |
| Glaze | 1096.58 | 0.799449 | 7149.56ms | 5373214 | 30 | 4.18685e+10 | 4.67296e+06 | 1.58024 | 5(Loss) | true |
