
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 3613.67 | 0.686471 | 6183.81ms | 16002592 | 40 | 3.36192e+10 | 4.2232e+06 | 2.93822 | 0.685053 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 3604.91 | 0.353772 | 6509.46ms | 16002592 | 40 | 8.97219e+09 | 4.23347e+06 | 0.882968 | 0.686767 | 1(Tie) | true |
