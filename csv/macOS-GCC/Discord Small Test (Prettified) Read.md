
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.25 | 0.916819 | 410.43ms | 6701 | 80 | 102825 | 3910.4 | 0.328407 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1606.48 | 0.701759 | 392.017ms | 6701 | 640 | 498753 | 3978 | 1.31971 | 1(Tie) | true |
| Glaze | 1478.2 | 1.30295 | 463.2ms | 6701 | 80 | 253838 | 4323.2 | 0.661765 | 3(Loss) | true |
| simdjson (reflection) | 1356.72 | 0.168285 | 492.356ms | 6701 | 4890 | 307254 | 4710.3 | 0.948494 | 4(Loss) | true |
| simdjson (ondemand) | 1191.85 | 0.209381 | 551.081ms | 6701 | 2560 | 322666 | 5361.9 | 0.0205109 | 5(Loss) | true |
