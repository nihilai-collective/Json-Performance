
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2190.54 | 0.104937 | 127.035ms | 2821 | 40 | 66.4385 | 1228.15 | 0.004071 | 1.10618 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 2182.75 | 0.15304 | 126.342ms | 2821 | 30 | 106.74 | 1232.53 | 0.113716 | 1.10904 | 1(Tie) | true |
