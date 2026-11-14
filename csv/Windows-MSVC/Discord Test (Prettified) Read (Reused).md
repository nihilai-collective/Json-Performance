
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2188.04 | 0.0390483 | 4115.22ms | 83958 | 2560 | 522703 | 36593.7 | 0.0472043 | 1.38817 | 1(Win) | true |
| Glaze | 2175 | 0.111588 | 4148.58ms | 83958 | 640 | 1.07998e+06 | 36813.1 | 0.00339541 | 1.39638 | 2(Loss) | true |
| Jsonifier | 1926.84 | 0.0309276 | 4624.38ms | 83958 | 4890 | 807669 | 41554.3 | 0.0480531 | 1.57645 | 3(Loss) | true |
| simdjson (ondemand) | 1434.97 | 0.0552423 | 5986.95ms | 83958 | 2560 | 2.43232e+06 | 55797.9 | 0.0348056 | 2.11714 | 4(Loss) | true |
