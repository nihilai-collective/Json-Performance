
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10822.7 | 0.201693 | 4202.89ms | 466906 | 160 | 1.10177e+06 | 41143 | 0.0656577 | 0.228611 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 10820.7 | 0.0604542 | 4178.67ms | 466906 | 4890 | 3.02629e+06 | 41150.4 | 0.0280054 | 0.228641 | 1(Tie) | true |
| simdjson (ondemand) | 8418.08 | 0.0904682 | 5457.85ms | 466906 | 4890 | 1.11978e+07 | 52895.2 | 0.715985 | 0.293935 | 3(Loss) | true |
| Glaze | 3460.66 | 0.0662201 | 6622.58ms | 466906 | 2560 | 1.85849e+07 | 128668 | 0.168551 | 0.715276 | 4(Loss) | true |
