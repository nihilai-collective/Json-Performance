
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.475 | 0.145061 | 7507.37ms | 56369 | 1280 | 1.5291e+07 | 75346.2 | 0.352194 | 3.46883 | 1(Win) | true |
| simdjson (ondemand) | 162.808 | 0.0768337 | 8472.86ms | 56369 | 640 | 4.11919e+07 | 330190 | 0.0239123 | 15.2056 | 2(Loss) | true |
